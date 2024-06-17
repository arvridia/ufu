#include "juncao.h"
#include "arquivo.h"
#include "pagina.h"

int _JOIN(FILE* fpr, entry_type_t rtype, FILE* fps, entry_type_t stype, buffer_size_t bsize, list_t* join_result, buffer_t* buffer_ptr);

int JOIN(FILE* fpr, entry_type_t rtype, FILE* fps, entry_type_t stype, buffer_size_t bsize, list_t* join_result){
    if(fpr == NULL || fps == NULL || join_result == NULL || !VALID_ENTRY_TYPE(rtype) || !VALID_ENTRY_TYPE(stype) || bsize <= 0) return 0;

    buffer_t buffer;
    if(!CREATE_BUFFER(bsize, &buffer)) return 0;


    page_value_t rval;
    if(!PAGES_PER_FILE(fpr, rtype, &rval)) return 0;

    *join_result = CREATE_LIST();

    buffer_size_t buffer_m2 = buffer.bsize - 2;


    if(rval < buffer_m2){

        if(!ADD_FILE_TO_BUFFER(&buffer, rtype, fpr)){
                DELETE_BUFFER(&buffer);
                return 0;
        }

        return(_JOIN(fpr, rtype, fps, stype, bsize, join_result, &buffer));
    }

    else{

        entry_number_t partition_number = rval % buffer_m2 == 0 ? rval / buffer_m2 : rval / buffer_m2 + 1;

        for(entry_number_t i = 0; i < partition_number; i++){
            if(!ADD_BLOCK_TO_BUFFER(&buffer, rtype, fpr, i * buffer_m2, (i+1) * buffer_m2)){
                DELETE_BUFFER(&buffer);
                return 0;
            }

            if(!_JOIN(fpr, rtype, fps, stype, bsize, join_result, &buffer)) return 0;
        }
        return 1;
    }
}

int _JOIN(FILE* fpr, entry_type_t rtype, FILE* fps, entry_type_t stype, buffer_size_t bsize, list_t* join_result, buffer_t* buffer_ptr){

    buffer_slot_t* first_slot;
    buffer_size_t first_slot_index;

    if(!FIND_FIRST_UNUSED_SLOT(buffer_ptr, &first_slot, &first_slot_index)){
        DELETE_BUFFER(buffer_ptr);
        return 0;
    }


    page_value_t svalue;


    page_t rpage, spage;

    if(!PAGES_PER_FILE(fps, stype, &svalue)){
        DELETE_BUFFER(buffer_ptr);
        return 0;
    }

    join_t* result;


    for(page_value_t i = 0; i < svalue; i++){


        if(!COPY_TO_PAGE(&first_slot->bentry, stype, fps, i * PAGE_SIZE)){
            DELETE_BUFFER(buffer_ptr);
            return 0;
        }


        spage = first_slot->bentry;


        for(buffer_size_t j = 0; i < buffer_ptr->bsize; j++){
            if(buffer_ptr->bslots[j]->bentry.ptype != rtype) continue;

            rpage = buffer_ptr->bslots[j]->bentry;

            for(page_value_t rentry = 0; rentry < rpage.psize; rentry++){
                for(page_value_t sentry = 0; sentry < spage.psize; sentry++){

                    if(SAME_KEY(&rpage.pvalues, rentry, rtype, sizeof(entry_number_t), &spage.pvalues, sentry, stype, sizeof(entry_number_t), CODIGO_CURSO_SIZE)){


                        if(!CREATE_ELEM(&rpage.pvalues, rentry, rtype, &spage.pvalues, sentry, stype, &result)){
                            DELETE_ELEM(result);
                            DELETE_LIST(join_result);
                            DELETE_BUFFER(buffer_ptr);
                            return 0;
                        }

                        if(!INSERT_AT_END(join_result, result)){
                            DELETE_ELEM(result);
                            DELETE_LIST(join_result);
                            DELETE_BUFFER(buffer_ptr);
                        }
                    }
                }
            }
        }
    }

    return 1;
}
